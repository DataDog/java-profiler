---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-20 07:04:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 208 |
| Sample Rate | 3.47/sec |
| Health Score | 217% |
| Threads | 10 |
| Allocations | 191 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 182 |
| Sample Rate | 3.03/sec |
| Health Score | 189% |
| Threads | 15 |
| Allocations | 97 |

<details>
<summary>CPU Timeline (3 unique values: 16-18 cores)</summary>

```
1795176021 18
1795176026 18
1795176031 18
1795176036 17
1795176041 17
1795176046 17
1795176051 17
1795176056 17
1795176061 17
1795176066 17
1795176071 17
1795176076 17
1795176081 17
1795176086 17
1795176091 17
1795176096 16
1795176101 16
1795176106 16
1795176111 16
1795176116 16
```
</details>

---

