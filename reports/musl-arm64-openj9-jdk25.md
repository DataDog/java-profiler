---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-23 10:56:48 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 326 |
| Sample Rate | 5.43/sec |
| Health Score | 339% |
| Threads | 13 |
| Allocations | 163 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 13 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (2 unique values: 41-46 cores)</summary>

```
1792767116 46
1792767121 46
1792767126 46
1792767131 46
1792767136 46
1792767141 46
1792767146 46
1792767151 46
1792767157 46
1792767162 46
1792767167 46
1792767172 46
1792767177 46
1792767182 46
1792767187 46
1792767192 46
1792767197 41
1792767202 41
1792767207 41
1792767212 41
```
</details>

---

