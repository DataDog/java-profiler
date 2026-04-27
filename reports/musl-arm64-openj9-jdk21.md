---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-27 05:15:08 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 299 |
| Sample Rate | 4.98/sec |
| Health Score | 311% |
| Threads | 12 |
| Allocations | 169 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 13 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1777281038 64
1777281043 64
1777281048 64
1777281053 64
1777281058 64
1777281063 64
1777281068 64
1777281073 64
1777281078 64
1777281083 64
1777281088 64
1777281093 64
1777281098 64
1777281104 64
1777281109 64
1777281114 64
1777281119 64
1777281124 64
1777281129 64
1777281134 64
```
</details>

---

