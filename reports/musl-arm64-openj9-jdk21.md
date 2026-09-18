---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 04:32:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 177 |
| Sample Rate | 2.95/sec |
| Health Score | 184% |
| Threads | 9 |
| Allocations | 94 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 240 |
| Sample Rate | 4.00/sec |
| Health Score | 250% |
| Threads | 14 |
| Allocations | 118 |

<details>
<summary>CPU Timeline (2 unique values: 25-30 cores)</summary>

```
1789720006 25
1789720011 25
1789720016 25
1789720021 25
1789720026 25
1789720031 25
1789720036 25
1789720041 25
1789720046 25
1789720051 30
1789720056 30
1789720061 30
1789720066 30
1789720071 30
1789720076 30
1789720081 30
1789720086 30
1789720091 30
1789720096 30
1789720101 30
```
</details>

---

