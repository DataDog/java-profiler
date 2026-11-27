---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-27 08:24:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 132 |
| Sample Rate | 2.20/sec |
| Health Score | 138% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 6 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (3 unique values: 70-93 cores)</summary>

```
1795785547 91
1795785552 91
1795785557 91
1795785562 91
1795785567 91
1795785572 91
1795785577 91
1795785582 91
1795785587 91
1795785592 91
1795785597 91
1795785602 91
1795785607 91
1795785612 91
1795785617 91
1795785622 93
1795785627 93
1795785632 93
1795785637 93
1795785642 93
```
</details>

---

