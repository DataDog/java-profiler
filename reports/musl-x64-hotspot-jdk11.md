---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-10 17:36:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 8 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 733 |
| Sample Rate | 12.22/sec |
| Health Score | 764% |
| Threads | 9 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (2 unique values: 36-40 cores)</summary>

```
1770762508 40
1770762513 40
1770762518 40
1770762523 40
1770762528 40
1770762533 40
1770762538 40
1770762543 36
1770762548 36
1770762553 36
1770762558 36
1770762563 36
1770762568 36
1770762573 36
1770762578 36
1770762583 36
1770762588 36
1770762593 36
1770762598 36
1770762603 36
```
</details>

---

