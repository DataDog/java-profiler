---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-19 09:18:50 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 235 |
| Sample Rate | 3.92/sec |
| Health Score | 245% |
| Threads | 10 |
| Allocations | 186 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 10 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1792415637 40
1792415642 40
1792415647 40
1792415652 40
1792415657 40
1792415662 40
1792415667 40
1792415672 40
1792415677 40
1792415682 40
1792415687 40
1792415692 40
1792415697 40
1792415702 40
1792415707 40
1792415712 40
1792415717 40
1792415722 40
1792415727 40
1792415732 40
```
</details>

---

