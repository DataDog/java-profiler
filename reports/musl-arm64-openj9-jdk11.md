---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-28 00:48:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 8 |
| Allocations | 46 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 8 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1790570619 38
1790570624 38
1790570629 38
1790570634 38
1790570639 38
1790570644 43
1790570649 43
1790570654 43
1790570659 43
1790570664 48
1790570669 48
1790570674 48
1790570679 48
1790570684 48
1790570689 48
1790570694 48
1790570699 48
1790570704 48
1790570709 48
1790570714 48
```
</details>

---

