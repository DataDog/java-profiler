---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-02 09:31:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 623 |
| Sample Rate | 10.38/sec |
| Health Score | 649% |
| Threads | 9 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (4 unique values: 55-69 cores)</summary>

```
1770042111 55
1770042116 55
1770042121 55
1770042126 55
1770042131 60
1770042136 60
1770042141 55
1770042146 55
1770042151 55
1770042156 55
1770042161 64
1770042166 64
1770042171 64
1770042176 64
1770042181 64
1770042186 64
1770042191 64
1770042196 64
1770042201 69
1770042206 69
```
</details>

---

