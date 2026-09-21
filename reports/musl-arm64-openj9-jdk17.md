---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-21 04:46:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 217 |
| Sample Rate | 3.62/sec |
| Health Score | 226% |
| Threads | 9 |
| Allocations | 152 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 11 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (2 unique values: 45-48 cores)</summary>

```
1789980033 45
1789980038 45
1789980043 45
1789980048 45
1789980053 45
1789980058 45
1789980063 48
1789980068 48
1789980073 48
1789980078 48
1789980083 48
1789980088 48
1789980093 48
1789980098 48
1789980103 48
1789980108 48
1789980113 48
1789980118 48
1789980123 48
1789980128 48
```
</details>

---

