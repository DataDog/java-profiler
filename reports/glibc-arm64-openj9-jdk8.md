---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-20 10:11:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 405 |
| Sample Rate | 6.75/sec |
| Health Score | 422% |
| Threads | 11 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 39 |
| Sample Rate | 0.65/sec |
| Health Score | 41% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 46-51 cores)</summary>

```
1792505038 49
1792505043 49
1792505048 49
1792505053 49
1792505058 49
1792505063 49
1792505068 46
1792505074 46
1792505079 46
1792505084 46
1792505089 46
1792505094 46
1792505099 46
1792505104 46
1792505109 46
1792505114 46
1792505119 46
1792505124 46
1792505129 46
1792505134 46
```
</details>

---

