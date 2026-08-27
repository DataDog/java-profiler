---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-27 09:40:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 9 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 324 |
| Sample Rate | 5.40/sec |
| Health Score | 338% |
| Threads | 15 |
| Allocations | 122 |

<details>
<summary>CPU Timeline (2 unique values: 39-44 cores)</summary>

```
1787837778 44
1787837783 44
1787837788 44
1787837793 44
1787837798 44
1787837803 44
1787837808 44
1787837813 44
1787837818 44
1787837823 44
1787837828 44
1787837833 39
1787837838 39
1787837843 39
1787837848 39
1787837853 39
1787837858 39
1787837863 39
1787837868 39
1787837873 39
```
</details>

---

