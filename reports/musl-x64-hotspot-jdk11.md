---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-09 16:19:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 791 |
| Sample Rate | 13.18/sec |
| Health Score | 824% |
| Threads | 9 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (2 unique values: 40-42 cores)</summary>

```
1794258873 40
1794258878 40
1794258883 40
1794258888 40
1794258893 40
1794258898 40
1794258903 42
1794258908 42
1794258913 42
1794258918 42
1794258923 42
1794258928 42
1794258933 42
1794258938 42
1794258943 42
1794258948 42
1794258953 40
1794258958 40
1794258963 40
1794258968 40
```
</details>

---

