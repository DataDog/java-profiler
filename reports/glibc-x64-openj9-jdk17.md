---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-01 15:37:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 621 |
| Sample Rate | 10.35/sec |
| Health Score | 647% |
| Threads | 10 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (3 unique values: 68-88 cores)</summary>

```
1788291137 76
1788291142 76
1788291147 76
1788291152 76
1788291157 76
1788291162 76
1788291167 76
1788291172 76
1788291177 76
1788291182 76
1788291187 76
1788291192 76
1788291197 76
1788291202 76
1788291207 68
1788291212 68
1788291217 68
1788291222 68
1788291227 68
1788291232 68
```
</details>

---

