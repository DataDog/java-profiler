---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 08:46:39 EDT

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 654 |
| Sample Rate | 10.90/sec |
| Health Score | 681% |
| Threads | 8 |
| Allocations | 414 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 11 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (3 unique values: 35-54 cores)</summary>

```
1792672952 35
1792672957 35
1792672962 35
1792672967 35
1792672972 43
1792672977 43
1792672982 43
1792672987 43
1792672992 43
1792672997 43
1792673002 43
1792673007 43
1792673012 43
1792673017 43
1792673022 43
1792673027 43
1792673032 43
1792673037 43
1792673042 43
1792673047 43
```
</details>

---

