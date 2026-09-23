---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-23 05:40:09 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 277 |
| Sample Rate | 4.62/sec |
| Health Score | 289% |
| Threads | 13 |
| Allocations | 139 |

<details>
<summary>CPU Timeline (2 unique values: 41-43 cores)</summary>

```
1790156086 41
1790156091 41
1790156096 41
1790156101 41
1790156106 41
1790156111 41
1790156116 41
1790156121 41
1790156126 41
1790156131 41
1790156136 41
1790156141 41
1790156146 41
1790156151 41
1790156156 41
1790156161 41
1790156166 41
1790156171 41
1790156176 41
1790156181 41
```
</details>

---

