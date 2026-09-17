---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-17 06:26:38 EDT

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 672 |
| Sample Rate | 11.20/sec |
| Health Score | 700% |
| Threads | 9 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 893 |
| Sample Rate | 14.88/sec |
| Health Score | 930% |
| Threads | 9 |
| Allocations | 557 |

<details>
<summary>CPU Timeline (4 unique values: 24-49 cores)</summary>

```
1789640524 26
1789640529 26
1789640534 26
1789640539 24
1789640544 24
1789640549 24
1789640554 24
1789640559 24
1789640564 24
1789640569 24
1789640574 24
1789640579 24
1789640584 24
1789640589 24
1789640594 24
1789640599 26
1789640604 26
1789640609 26
1789640614 26
1789640619 26
```
</details>

---

