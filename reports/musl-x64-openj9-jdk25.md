---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 15:22:41 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 423 |
| Sample Rate | 7.05/sec |
| Health Score | 441% |
| Threads | 8 |
| Allocations | 438 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 604 |
| Sample Rate | 10.07/sec |
| Health Score | 629% |
| Threads | 10 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1794341783 32
1794341788 32
1794341793 32
1794341798 32
1794341803 32
1794341808 32
1794341813 32
1794341818 32
1794341823 32
1794341828 32
1794341833 32
1794341838 32
1794341843 32
1794341848 32
1794341853 32
1794341858 32
1794341863 32
1794341868 32
1794341873 32
1794341878 32
```
</details>

---

