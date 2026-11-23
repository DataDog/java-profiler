---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-23 11:59:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 12 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 12 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (4 unique values: 48-53 cores)</summary>

```
1795452955 53
1795452960 51
1795452965 51
1795452970 51
1795452975 51
1795452980 49
1795452985 49
1795452990 49
1795452995 49
1795453000 49
1795453005 49
1795453010 49
1795453015 48
1795453020 48
1795453025 48
1795453030 48
1795453035 53
1795453040 53
1795453045 53
1795453050 51
```
</details>

---

