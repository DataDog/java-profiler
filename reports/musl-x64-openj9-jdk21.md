---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-13 07:26:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 759 |
| Sample Rate | 12.65/sec |
| Health Score | 791% |
| Threads | 10 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (4 unique values: 68-73 cores)</summary>

```
1794572487 71
1794572492 71
1794572497 73
1794572502 73
1794572507 68
1794572512 68
1794572517 68
1794572522 68
1794572527 68
1794572532 70
1794572537 70
1794572542 70
1794572547 70
1794572552 70
1794572557 70
1794572562 70
1794572567 70
1794572572 70
1794572577 70
1794572582 70
```
</details>

---

