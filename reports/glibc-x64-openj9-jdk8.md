---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-20 10:11:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 196 |
| Sample Rate | 3.27/sec |
| Health Score | 204% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 185 |
| Sample Rate | 3.08/sec |
| Health Score | 192% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 90-96 cores)</summary>

```
1792505049 92
1792505054 92
1792505059 94
1792505064 94
1792505069 94
1792505074 94
1792505079 94
1792505084 92
1792505089 92
1792505094 92
1792505099 94
1792505104 94
1792505109 94
1792505114 94
1792505119 94
1792505124 94
1792505129 96
1792505134 96
1792505139 96
1792505144 96
```
</details>

---

