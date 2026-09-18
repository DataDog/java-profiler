---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 04:33:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 447 |
| Sample Rate | 7.45/sec |
| Health Score | 466% |
| Threads | 12 |
| Allocations | 223 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 914 |
| Sample Rate | 15.23/sec |
| Health Score | 952% |
| Threads | 9 |
| Allocations | 417 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1789720017 46
1789720022 46
1789720027 46
1789720032 46
1789720037 46
1789720042 46
1789720047 46
1789720052 46
1789720057 46
1789720062 46
1789720067 46
1789720072 46
1789720077 46
1789720082 48
1789720087 48
1789720093 48
1789720098 48
1789720103 48
1789720108 48
1789720113 48
```
</details>

---

