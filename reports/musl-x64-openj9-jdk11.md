---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-22 09:50:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1022 |
| Sample Rate | 17.03/sec |
| Health Score | 1064% |
| Threads | 10 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1790084778 32
1790084783 32
1790084788 32
1790084793 32
1790084798 32
1790084803 32
1790084808 32
1790084813 32
1790084818 32
1790084823 32
1790084828 32
1790084833 32
1790084838 32
1790084843 32
1790084848 32
1790084853 32
1790084858 32
1790084863 32
1790084868 32
1790084873 32
```
</details>

---

