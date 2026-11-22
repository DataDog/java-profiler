---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-22 16:32:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 9 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 698 |
| Sample Rate | 11.63/sec |
| Health Score | 727% |
| Threads | 11 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (3 unique values: 63-68 cores)</summary>

```
1795382917 65
1795382922 65
1795382927 65
1795382932 65
1795382937 63
1795382942 63
1795382947 63
1795382952 63
1795382957 63
1795382962 63
1795382967 63
1795382972 63
1795382977 63
1795382982 63
1795382987 63
1795382992 63
1795382997 63
1795383002 63
1795383007 63
1795383012 63
```
</details>

---

