---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-22 12:39:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 859 |
| Sample Rate | 14.32/sec |
| Health Score | 895% |
| Threads | 10 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (3 unique values: 40-43 cores)</summary>

```
1792686786 42
1792686791 42
1792686796 42
1792686801 42
1792686806 42
1792686811 42
1792686816 42
1792686821 42
1792686826 40
1792686831 40
1792686836 40
1792686841 40
1792686846 40
1792686851 40
1792686856 40
1792686861 40
1792686866 43
1792686871 43
1792686876 43
1792686881 43
```
</details>

---

