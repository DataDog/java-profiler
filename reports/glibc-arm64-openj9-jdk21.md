---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 06:06:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 298 |
| Sample Rate | 4.97/sec |
| Health Score | 311% |
| Threads | 11 |
| Allocations | 150 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1795086097 46
1795086102 46
1795086107 46
1795086112 46
1795086117 46
1795086122 46
1795086127 46
1795086132 46
1795086137 46
1795086142 51
1795086147 51
1795086152 51
1795086157 51
1795086162 51
1795086167 51
1795086172 51
1795086177 51
1795086182 51
1795086187 51
1795086192 51
```
</details>

---

