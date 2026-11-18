---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 12:33:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 438 |
| Sample Rate | 7.30/sec |
| Health Score | 456% |
| Threads | 8 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 10 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (2 unique values: 25-46 cores)</summary>

```
1795022946 25
1795022951 25
1795022956 25
1795022961 25
1795022966 25
1795022971 25
1795022976 25
1795022981 25
1795022986 25
1795022991 25
1795022996 25
1795023001 25
1795023006 25
1795023011 25
1795023016 25
1795023021 25
1795023026 25
1795023031 46
1795023036 46
1795023041 46
```
</details>

---

