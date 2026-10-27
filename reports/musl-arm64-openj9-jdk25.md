---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-27 16:51:57 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 9 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 298 |
| Sample Rate | 4.97/sec |
| Health Score | 311% |
| Threads | 13 |
| Allocations | 158 |

<details>
<summary>CPU Timeline (3 unique values: 33-45 cores)</summary>

```
1793133916 40
1793133921 40
1793133926 40
1793133931 40
1793133936 40
1793133941 40
1793133946 40
1793133951 40
1793133956 40
1793133961 45
1793133966 45
1793133971 45
1793133976 45
1793133981 45
1793133986 45
1793133991 45
1793133996 45
1793134001 45
1793134006 45
1793134011 45
```
</details>

---

