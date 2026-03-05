---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-03-05 15:44:31 EST

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 485 |
| Sample Rate | 8.08/sec |
| Health Score | 505% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 686 |
| Sample Rate | 11.43/sec |
| Health Score | 714% |
| Threads | 9 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (3 unique values: 27-32 cores)</summary>

```
1772742886 27
1772742891 27
1772742896 27
1772742901 27
1772742906 27
1772742911 27
1772742916 27
1772742921 32
1772742926 32
1772742931 28
1772742936 28
1772742941 28
1772742946 28
1772742951 28
1772742956 28
1772742961 28
1772742966 28
1772742971 28
1772742976 28
1772742981 28
```
</details>

---

