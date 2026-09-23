---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-23 10:08:39 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 260 |
| Sample Rate | 4.33/sec |
| Health Score | 271% |
| Threads | 10 |
| Allocations | 137 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790172157 48
1790172162 48
1790172167 48
1790172172 48
1790172177 43
1790172182 43
1790172187 43
1790172192 43
1790172197 43
1790172202 43
1790172207 43
1790172212 43
1790172218 43
1790172223 43
1790172228 43
1790172233 43
1790172238 48
1790172243 48
1790172248 48
1790172253 48
```
</details>

---

