---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-22 12:29:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 13 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 131 |
| Sample Rate | 2.18/sec |
| Health Score | 136% |
| Threads | 7 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 830 |
| Sample Rate | 13.83/sec |
| Health Score | 864% |
| Threads | 10 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (2 unique values: 13-48 cores)</summary>

```
1792686138 13
1792686143 13
1792686148 13
1792686153 13
1792686158 13
1792686163 13
1792686168 48
1792686173 48
1792686178 48
1792686183 48
1792686188 48
1792686193 48
1792686198 48
1792686203 48
1792686208 48
1792686213 48
1792686218 48
1792686223 48
1792686228 48
1792686233 48
```
</details>

---

