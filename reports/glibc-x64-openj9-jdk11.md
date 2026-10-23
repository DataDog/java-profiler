---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-23 16:04:37 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 847 |
| Sample Rate | 14.12/sec |
| Health Score | 882% |
| Threads | 10 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1792785527 28
1792785532 28
1792785537 28
1792785542 28
1792785547 30
1792785552 30
1792785557 30
1792785562 30
1792785567 30
1792785572 30
1792785577 30
1792785582 30
1792785587 30
1792785592 30
1792785597 30
1792785602 30
1792785607 30
1792785612 30
1792785617 30
1792785622 30
```
</details>

---

