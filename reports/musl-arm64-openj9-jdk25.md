---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-23 09:48:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 267 |
| Sample Rate | 4.45/sec |
| Health Score | 278% |
| Threads | 12 |
| Allocations | 181 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790171077 50
1790171082 50
1790171087 50
1790171092 50
1790171097 50
1790171102 50
1790171107 50
1790171112 50
1790171117 50
1790171122 50
1790171127 50
1790171132 50
1790171137 50
1790171142 50
1790171147 50
1790171152 50
1790171157 50
1790171162 50
1790171167 50
1790171172 50
```
</details>

---

