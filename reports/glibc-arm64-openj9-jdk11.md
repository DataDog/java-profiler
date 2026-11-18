---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 00:06:51 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 310 |
| Sample Rate | 5.17/sec |
| Health Score | 323% |
| Threads | 11 |
| Allocations | 205 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 13 |
| Allocations | 77 |

<details>
<summary>CPU Timeline (2 unique values: 24-29 cores)</summary>

```
1794978138 24
1794978143 24
1794978148 24
1794978153 24
1794978158 24
1794978163 24
1794978168 24
1794978173 24
1794978178 24
1794978183 24
1794978188 24
1794978193 24
1794978198 24
1794978203 24
1794978208 29
1794978213 29
1794978218 29
1794978223 29
1794978228 29
1794978233 29
```
</details>

---

