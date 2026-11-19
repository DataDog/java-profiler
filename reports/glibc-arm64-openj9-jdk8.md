---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-19 13:36:48 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 6 |
| Sample Rate | 0.10/sec |
| Health Score | 6% |
| Threads | 6 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 32-50 cores)</summary>

```
1795113142 50
1795113147 50
1795113152 49
1795113157 49
1795113162 49
1795113167 49
1795113172 49
1795113177 49
1795113182 49
1795113187 49
1795113192 49
1795113197 49
1795113202 50
1795113207 50
1795113212 50
1795113217 50
1795113222 50
1795113227 50
1795113232 36
1795113237 36
```
</details>

---

