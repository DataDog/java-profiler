---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-23 10:08:39 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 8 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 730 |
| Sample Rate | 12.17/sec |
| Health Score | 761% |
| Threads | 9 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (2 unique values: 34-36 cores)</summary>

```
1790172152 34
1790172157 34
1790172162 34
1790172167 34
1790172172 34
1790172177 34
1790172182 34
1790172187 34
1790172192 34
1790172197 34
1790172202 34
1790172207 34
1790172212 36
1790172217 36
1790172222 36
1790172227 36
1790172232 36
1790172237 36
1790172243 36
1790172248 36
```
</details>

---

