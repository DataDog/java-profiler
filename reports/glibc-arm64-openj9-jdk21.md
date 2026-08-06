---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-06 07:56:20 EDT

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 8 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 14 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (4 unique values: 36-54 cores)</summary>

```
1786017184 54
1786017189 41
1786017194 41
1786017199 41
1786017204 41
1786017209 41
1786017214 41
1786017219 41
1786017224 41
1786017229 41
1786017234 41
1786017239 41
1786017244 36
1786017249 36
1786017254 36
1786017259 36
1786017264 41
1786017269 41
1786017274 41
1786017279 41
```
</details>

---

