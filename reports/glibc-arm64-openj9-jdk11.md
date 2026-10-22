---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 12:29:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 11 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 12 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (2 unique values: 46-54 cores)</summary>

```
1792686172 54
1792686177 54
1792686182 54
1792686187 54
1792686192 46
1792686197 46
1792686202 46
1792686207 46
1792686212 46
1792686217 46
1792686222 46
1792686227 46
1792686232 46
1792686237 46
1792686242 46
1792686247 46
1792686252 46
1792686257 46
1792686262 46
1792686267 46
```
</details>

---

