---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-17 17:59:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 8 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 13 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (2 unique values: 26-28 cores)</summary>

```
1789682066 26
1789682071 26
1789682076 26
1789682081 26
1789682086 26
1789682091 26
1789682096 26
1789682101 26
1789682106 26
1789682111 26
1789682116 26
1789682121 26
1789682126 26
1789682131 26
1789682136 26
1789682141 26
1789682146 28
1789682151 28
1789682156 28
1789682161 28
```
</details>

---

