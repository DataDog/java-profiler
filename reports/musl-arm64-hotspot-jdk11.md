---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-28 00:48:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 178 |
| Sample Rate | 2.97/sec |
| Health Score | 186% |
| Threads | 7 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 954 |
| Sample Rate | 15.90/sec |
| Health Score | 994% |
| Threads | 9 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790570654 43
1790570659 43
1790570664 43
1790570669 43
1790570674 43
1790570679 43
1790570684 43
1790570689 43
1790570694 43
1790570699 43
1790570704 48
1790570709 48
1790570714 48
1790570719 48
1790570724 48
1790570729 48
1790570734 48
1790570739 48
1790570744 48
1790570749 48
```
</details>

---

