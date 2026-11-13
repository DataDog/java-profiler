---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 07:26:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 9 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (3 unique values: 38-63 cores)</summary>

```
1794572477 43
1794572482 43
1794572487 43
1794572492 43
1794572497 43
1794572502 43
1794572507 43
1794572512 63
1794572517 63
1794572522 63
1794572527 63
1794572532 63
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

