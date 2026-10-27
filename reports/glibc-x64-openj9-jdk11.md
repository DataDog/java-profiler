---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-27 14:46:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
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
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 8 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 871 |
| Sample Rate | 14.52/sec |
| Health Score | 907% |
| Threads | 10 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1793126482 32
1793126487 32
1793126492 32
1793126497 32
1793126502 32
1793126507 32
1793126512 32
1793126517 32
1793126522 32
1793126527 32
1793126532 32
1793126537 32
1793126542 32
1793126547 32
1793126552 32
1793126557 32
1793126562 32
1793126567 32
1793126572 32
1793126577 32
```
</details>

---

