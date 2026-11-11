---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-11 09:57:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 11 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 831 |
| Sample Rate | 13.85/sec |
| Health Score | 866% |
| Threads | 11 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (2 unique values: 41-46 cores)</summary>

```
1794408772 46
1794408777 46
1794408782 46
1794408787 46
1794408792 46
1794408797 46
1794408802 46
1794408807 46
1794408812 46
1794408817 46
1794408822 46
1794408827 46
1794408832 46
1794408837 46
1794408842 41
1794408847 41
1794408852 41
1794408857 41
1794408862 41
1794408867 41
```
</details>

---

