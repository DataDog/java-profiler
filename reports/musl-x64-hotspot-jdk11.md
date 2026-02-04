---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-04 14:09:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 793 |
| Sample Rate | 13.22/sec |
| Health Score | 826% |
| Threads | 9 |
| Allocations | 552 |

<details>
<summary>CPU Timeline (5 unique values: 49-63 cores)</summary>

```
1770231805 56
1770231810 56
1770231815 56
1770231820 56
1770231825 56
1770231830 63
1770231835 63
1770231840 57
1770231845 57
1770231850 49
1770231855 49
1770231860 49
1770231865 49
1770231870 49
1770231875 49
1770231880 49
1770231885 49
1770231890 49
1770231895 49
1770231900 49
```
</details>

---

