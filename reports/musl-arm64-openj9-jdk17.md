---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-02 11:54:33 EST

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 7 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 7 |
| Sample Rate | 0.12/sec |
| Health Score | 8% |
| Threads | 5 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (4 unique values: 42-47 cores)</summary>

```
1793638074 42
1793638079 42
1793638084 46
1793638089 46
1793638094 47
1793638099 47
1793638104 47
1793638109 47
1793638114 45
1793638119 45
1793638124 45
1793638129 45
1793638134 45
1793638139 45
1793638144 46
1793638150 46
1793638155 46
1793638160 46
1793638165 46
1793638170 46
```
</details>

---

