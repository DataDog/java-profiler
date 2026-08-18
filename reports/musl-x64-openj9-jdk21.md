---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-18 09:21:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 9 |
| Allocations | 418 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 677 |
| Sample Rate | 11.28/sec |
| Health Score | 705% |
| Threads | 11 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (3 unique values: 88-96 cores)</summary>

```
1787059004 94
1787059009 94
1787059014 94
1787059019 96
1787059024 96
1787059029 96
1787059034 96
1787059039 96
1787059044 96
1787059049 96
1787059054 96
1787059059 96
1787059064 96
1787059069 96
1787059074 96
1787059079 96
1787059084 96
1787059089 96
1787059094 96
1787059099 88
```
</details>

---

