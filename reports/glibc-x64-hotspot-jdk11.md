---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-23 05:40:10 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 8 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 847 |
| Sample Rate | 14.12/sec |
| Health Score | 882% |
| Threads | 10 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (5 unique values: 35-59 cores)</summary>

```
1790156101 40
1790156106 40
1790156111 40
1790156116 40
1790156121 40
1790156126 40
1790156131 40
1790156136 44
1790156141 44
1790156146 39
1790156151 39
1790156156 39
1790156161 39
1790156166 39
1790156171 39
1790156176 39
1790156181 39
1790156186 39
1790156191 39
1790156196 39
```
</details>

---

