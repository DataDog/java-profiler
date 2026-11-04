---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-04 17:02:39 EST

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 408 |
| Sample Rate | 6.80/sec |
| Health Score | 425% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 11 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (3 unique values: 35-45 cores)</summary>

```
1793829486 35
1793829491 35
1793829496 35
1793829501 35
1793829506 35
1793829511 35
1793829516 35
1793829521 35
1793829526 40
1793829531 40
1793829536 40
1793829541 40
1793829546 40
1793829551 40
1793829556 40
1793829561 40
1793829566 40
1793829571 40
1793829576 40
1793829581 40
```
</details>

---

