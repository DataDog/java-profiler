---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-17 09:09:13 EDT

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
| CPU Cores (start) | 12 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 12 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (1 unique values: 12-12 cores)</summary>

```
1786971653 12
1786971658 12
1786971663 12
1786971668 12
1786971673 12
1786971678 12
1786971683 12
1786971688 12
1786971693 12
1786971698 12
1786971703 12
1786971708 12
1786971713 12
1786971718 12
1786971723 12
1786971728 12
1786971733 12
1786971738 12
1786971743 12
1786971748 12
```
</details>

---

