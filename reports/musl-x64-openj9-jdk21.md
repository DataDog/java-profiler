---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-22 13:25:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 802 |
| Sample Rate | 13.37/sec |
| Health Score | 836% |
| Threads | 12 |
| Allocations | 553 |

<details>
<summary>CPU Timeline (2 unique values: 85-87 cores)</summary>

```
1792689725 87
1792689730 87
1792689735 87
1792689740 87
1792689745 87
1792689750 87
1792689755 87
1792689760 87
1792689765 87
1792689770 87
1792689775 87
1792689780 85
1792689785 85
1792689790 85
1792689795 85
1792689800 87
1792689805 87
1792689810 87
1792689815 85
1792689820 85
```
</details>

---

