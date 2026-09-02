---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-02 00:58:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 11 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 208 |
| Sample Rate | 3.47/sec |
| Health Score | 217% |
| Threads | 14 |
| Allocations | 112 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1788324839 38
1788324844 38
1788324849 38
1788324854 43
1788324859 43
1788324864 43
1788324869 43
1788324874 43
1788324879 43
1788324884 43
1788324889 43
1788324894 43
1788324899 43
1788324904 43
1788324909 43
1788324914 43
1788324919 43
1788324924 43
1788324929 43
1788324934 43
```
</details>

---

