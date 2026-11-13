---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 07:27:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 233 |
| Sample Rate | 3.88/sec |
| Health Score | 242% |
| Threads | 11 |
| Allocations | 180 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 286 |
| Sample Rate | 4.77/sec |
| Health Score | 298% |
| Threads | 14 |
| Allocations | 116 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1794572477 43
1794572482 43
1794572487 43
1794572492 43
1794572497 43
1794572502 43
1794572507 43
1794572512 43
1794572517 43
1794572522 43
1794572527 38
1794572532 38
1794572537 38
1794572542 38
1794572547 38
1794572552 38
1794572557 38
1794572562 38
1794572567 38
1794572572 38
```
</details>

---

