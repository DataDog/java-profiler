---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-18 02:29:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 17 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 217 |
| Sample Rate | 3.62/sec |
| Health Score | 226% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 282 |
| Sample Rate | 4.70/sec |
| Health Score | 294% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 15-17 cores)</summary>

```
1789712720 17
1789712725 17
1789712730 17
1789712735 17
1789712740 17
1789712746 17
1789712751 17
1789712756 17
1789712761 17
1789712766 17
1789712771 17
1789712776 15
1789712781 15
1789712786 15
1789712791 15
1789712796 15
1789712801 15
1789712806 15
1789712811 15
1789712816 15
```
</details>

---

