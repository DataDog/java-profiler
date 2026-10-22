---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 12:29:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 8 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 12 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (3 unique values: 53-64 cores)</summary>

```
1792686157 54
1792686162 54
1792686167 54
1792686172 54
1792686177 54
1792686182 54
1792686187 54
1792686192 54
1792686197 54
1792686202 54
1792686207 54
1792686212 54
1792686217 54
1792686222 54
1792686227 54
1792686232 64
1792686237 64
1792686242 64
1792686247 64
1792686252 64
```
</details>

---

