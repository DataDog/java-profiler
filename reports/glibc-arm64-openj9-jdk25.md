---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-20 12:39:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
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
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 9 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795196152 50
1795196157 50
1795196162 50
1795196167 50
1795196172 50
1795196177 50
1795196182 50
1795196187 50
1795196192 50
1795196197 50
1795196202 50
1795196207 50
1795196212 50
1795196217 50
1795196222 50
1795196227 50
1795196232 50
1795196237 50
1795196242 50
1795196247 50
```
</details>

---

