---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 09:26:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 691 |
| Sample Rate | 11.52/sec |
| Health Score | 720% |
| Threads | 8 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (3 unique values: 20-26 cores)</summary>

```
1794406936 22
1794406941 22
1794406946 22
1794406951 22
1794406956 22
1794406961 22
1794406966 20
1794406971 20
1794406976 20
1794406981 20
1794406986 20
1794406991 20
1794406996 26
1794407001 26
1794407006 26
1794407011 26
1794407016 26
1794407021 26
1794407026 26
1794407031 26
```
</details>

---

