---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-23 13:49:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 506 |
| Sample Rate | 8.43/sec |
| Health Score | 527% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 8 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (4 unique values: 34-55 cores)</summary>

```
1792777530 36
1792777535 36
1792777540 36
1792777545 36
1792777550 36
1792777555 36
1792777560 36
1792777565 36
1792777570 36
1792777575 36
1792777580 36
1792777585 34
1792777590 34
1792777595 34
1792777600 34
1792777605 34
1792777610 34
1792777615 34
1792777620 34
1792777626 34
```
</details>

---

