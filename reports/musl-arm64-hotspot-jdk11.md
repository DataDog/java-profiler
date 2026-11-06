---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-06 15:13:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1004 |
| Sample Rate | 16.73/sec |
| Health Score | 1046% |
| Threads | 10 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793995747 48
1793995752 48
1793995757 48
1793995762 48
1793995767 48
1793995772 48
1793995777 48
1793995782 48
1793995787 48
1793995792 48
1793995797 48
1793995802 48
1793995807 48
1793995812 48
1793995817 48
1793995822 48
1793995827 48
1793995832 48
1793995837 48
1793995842 48
```
</details>

---

